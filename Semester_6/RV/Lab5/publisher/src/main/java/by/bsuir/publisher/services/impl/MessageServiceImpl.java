package by.bsuir.publisher.services.impl;

import by.bsuir.publisher.dto.MessageActionDto;
import by.bsuir.publisher.dto.MessageActionTypeDto;
import by.bsuir.publisher.dto.requests.MessageRequestDto;
import by.bsuir.publisher.dto.responses.ErrorDto;
import by.bsuir.publisher.dto.responses.MessageResponseDto;
import by.bsuir.publisher.dto.responses.converters.MessageResponseConverter;
import by.bsuir.publisher.exceptions.Messages;
import by.bsuir.publisher.exceptions.NoEntityExistsException;
import by.bsuir.publisher.exceptions.ServiceException;
import by.bsuir.publisher.repositories.MessageCacheRepository;
import by.bsuir.publisher.repositories.StoryRepository;
import by.bsuir.publisher.services.MessageService;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.common.header.internals.RecordHeader;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.requestreply.ReplyingKafkaTemplate;
import org.springframework.kafka.requestreply.RequestReplyFuture;
import org.springframework.kafka.support.KafkaHeaders;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.TimeUnit;

@Service
@RequiredArgsConstructor
@Validated
@Transactional(rollbackFor = {ServiceException.class})
public class MessageServiceImpl implements MessageService {
    private final ObjectMapper objectMapper;
    private final MessageResponseConverter messageResponseConverter;
    private final MessageCacheRepository messageCacheRepository;
    private final StoryRepository storyRepository;

    private final ReplyingKafkaTemplate<String, MessageActionDto, MessageActionDto> replyingKafkaTemplate;

    @Value("${topic.inTopic}")
    private String inTopic;

    @Value("${topic.outTopic}")
    private String outTopic;

    @KafkaListener(topics = "${topic.messageChangeTopic}")
    protected void receiveMessageChange(MessageActionDto messageActionDto) {
        switch (messageActionDto.getAction()) {
            case CREATE, UPDATE -> {
                MessageResponseDto messageResponseDto = objectMapper.
                        convertValue(messageActionDto.getData(), MessageResponseDto.class);
                messageCacheRepository.save(messageResponseConverter.fromDto(messageResponseDto));
            }
            case DELETE -> {
                Long id = Long.valueOf((String) messageActionDto.getData());
                messageCacheRepository.deleteById(id);
            }
        }
    }

    protected MessageActionDto sendMessageAction(MessageActionDto messageActionDto) {
        ProducerRecord<String, MessageActionDto> record = new ProducerRecord<>(inTopic, null,
                System.currentTimeMillis(), String.valueOf(messageActionDto.toString()),
                messageActionDto);
        record.headers().add(new RecordHeader(KafkaHeaders.REPLY_TOPIC, outTopic.getBytes()));
        RequestReplyFuture<String, MessageActionDto, MessageActionDto> response = replyingKafkaTemplate.sendAndReceive(record);
        return response.orTimeout(1000, TimeUnit.MILLISECONDS).join().value();
    }

    @Override
    public MessageResponseDto create(@NonNull MessageRequestDto dto) throws ServiceException, NoEntityExistsException {
        storyRepository.findById(dto.getStoryId()).orElseThrow(() ->
                new NoEntityExistsException(Messages.NoEntityExistsException));
        //Synchronous, as response in tests shall contain created message id, and if passed id is null,
        //asynchronous messaging is not appropriate(we won't be able to obtain generated id)
        MessageActionDto action = sendMessageAction(MessageActionDto.builder().
                action(MessageActionTypeDto.CREATE).
                data(dto).
                build());
        MessageResponseDto response = objectMapper.convertValue(action.getData(), MessageResponseDto.class);
        if (ObjectUtils.allNull(response.getId(), response.getStoryId(), response.getContent())) {
            throw new ServiceException(objectMapper.convertValue(action.getData(), ErrorDto.class));
        }
        messageCacheRepository.save(messageResponseConverter.fromDto(response));
        return response;
    }

    @Override
    public Optional<MessageResponseDto> read(@NonNull Long uuid) {
        return Optional.ofNullable(messageCacheRepository.findById(uuid).map(messageResponseConverter::toDto).orElseGet(() -> {
            MessageActionDto action = sendMessageAction(MessageActionDto.builder().
                    action(MessageActionTypeDto.READ).
                    data(String.valueOf(uuid)).
                    build());
            return objectMapper.convertValue(action.getData(), MessageResponseDto.class);
        }));
    }

    @Override
    @SuppressWarnings({"unchecked", "rawtypes"})
    public List<MessageResponseDto> readAll() {
        return (List<MessageResponseDto>) ((List)sendMessageAction(MessageActionDto.builder().
                action(MessageActionTypeDto.READ_ALL).
                build()).getData()).stream().map(v -> objectMapper.convertValue(v, MessageResponseDto.class)).toList();
    }

    @Override
    public MessageResponseDto update(@NonNull MessageRequestDto dto) throws ServiceException {
        MessageActionDto action = sendMessageAction(MessageActionDto.builder().
                action(MessageActionTypeDto.UPDATE).
                data(dto).
                build());
       MessageResponseDto response = objectMapper.convertValue(action.getData(), MessageResponseDto.class);
       if (ObjectUtils.allNull(response.getId(), response.getContent(), response.getStoryId())) {
           throw new ServiceException(objectMapper.convertValue(action.getData(), ErrorDto.class));
       }
       messageCacheRepository.save(messageResponseConverter.fromDto(response));
       return response;
    }

    @Override
    public Long delete(@NonNull Long uuid) throws ServiceException {
        MessageActionDto action = sendMessageAction(MessageActionDto.builder().
                action(MessageActionTypeDto.DELETE).
                data(String.valueOf(uuid)).
                build());
        try {
            messageCacheRepository.deleteById(uuid);
            return Long.valueOf((Integer) action.getData());
        } catch (ClassCastException e) {
            throw new ServiceException(objectMapper.convertValue(action.getData(), ErrorDto.class));
        }
    }
}
