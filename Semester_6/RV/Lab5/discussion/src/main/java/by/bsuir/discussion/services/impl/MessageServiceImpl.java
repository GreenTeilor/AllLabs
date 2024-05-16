package by.bsuir.discussion.services.impl;

import by.bsuir.discussion.domain.Message;
import by.bsuir.discussion.dto.MessageActionDto;
import by.bsuir.discussion.dto.MessageActionTypeDto;
import by.bsuir.discussion.dto.requests.MessageRequestDto;
import by.bsuir.discussion.dto.requests.converters.MessageRequestConverter;
import by.bsuir.discussion.dto.responses.MessageResponseDto;
import by.bsuir.discussion.dto.responses.converters.CollectionMessageResponseConverter;
import by.bsuir.discussion.dto.responses.converters.MessageResponseConverter;
import by.bsuir.discussion.exceptions.EntityExistsException;
import by.bsuir.discussion.exceptions.ErrorDto;
import by.bsuir.discussion.exceptions.Messages;
import by.bsuir.discussion.exceptions.NoEntityExistsException;
import by.bsuir.discussion.repositories.MessageRepository;
import by.bsuir.discussion.services.MessageService;
import com.fasterxml.jackson.databind.ObjectMapper;
import jakarta.validation.Valid;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Lazy;
import org.springframework.http.HttpStatus;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;

import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
@Validated
@Transactional(rollbackFor = {EntityExistsException.class, NoEntityExistsException.class})
public class MessageServiceImpl implements MessageService {

    private final MessageRepository messageRepository;
    private final MessageRequestConverter messageRequestConverter;
    private final MessageResponseConverter messageResponseConverter;
    private final CollectionMessageResponseConverter collectionMessageResponseConverter;
    private final ObjectMapper objectMapper;
    private final KafkaTemplate<String, MessageActionDto> kafkaMessageActionTemplate;

    @Value("${topic.messageChangeTopic}")
    private String messageChangeTopic;

    private MessageService messageService;

    @Autowired
    public void setMessageService(@Lazy MessageService messageService) {
        this.messageService = messageService;
    }

    @KafkaListener(topics = "${topic.inTopic}")
    @SendTo
    protected MessageActionDto receive(MessageActionDto messageActionDto) {
        System.out.println("Received message: " + messageActionDto);
        switch (messageActionDto.getAction()) {
            case CREATE -> {
                try {
                    MessageRequestDto messageRequest = objectMapper.convertValue(messageActionDto.getData(),
                            MessageRequestDto.class);
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.CREATE).
                            data(messageService.create(messageRequest)).
                            build();
                } catch (EntityExistsException e) {
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.CREATE).
                            data(ErrorDto.builder().
                                    code(HttpStatus.BAD_REQUEST.value() + "00").
                                    message(Messages.EntityExistsException).
                                    build()).
                            build();
                }
            }
            case READ -> {
                Long id = Long.valueOf((String) messageActionDto.getData());
                return MessageActionDto.builder().
                        action(MessageActionTypeDto.READ).
                        data(messageService.read(id)).
                        build();
            }
            case READ_ALL -> {
                return MessageActionDto.builder().
                        action(MessageActionTypeDto.READ_ALL).
                        data(messageService.readAll()).
                        build();
            }
            case UPDATE -> {
                try {
                    MessageRequestDto messageRequest = objectMapper.convertValue(messageActionDto.getData(),
                            MessageRequestDto.class);
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.UPDATE).
                            data(messageService.update(messageRequest)).
                            build();
                } catch (NoEntityExistsException e) {
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.UPDATE).
                            data(ErrorDto.builder().
                                    code(HttpStatus.BAD_REQUEST.value() + "00").
                                    message(Messages.NoEntityExistsException).
                                    build()).
                            build();
                }
            }
            case DELETE -> {
                try {
                    Long id = Long.valueOf((String) messageActionDto.getData());
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.DELETE).
                            data(messageService.delete(id)).
                            build();
                } catch (NoEntityExistsException e) {
                    return MessageActionDto.builder().
                            action(MessageActionTypeDto.DELETE).
                            data(ErrorDto.builder().
                                    code(HttpStatus.BAD_REQUEST.value() + "00").
                                    message(Messages.NoEntityExistsException).
                                    build()).
                            build();
                }
            }
        }
        return messageActionDto;
    }

    @Override
    @Validated
    public MessageResponseDto create(@Valid @NonNull MessageRequestDto dto) throws EntityExistsException {
        Optional<Message> message = dto.getId() == null ? Optional.empty() : messageRepository.findMessageById(dto.getId());
        if (message.isEmpty()) {
            Message entity = messageRequestConverter.fromDto(dto);
            if (dto.getId() == null) {
                entity.setId((long) (Math.random() * 2_000_000_000L) + 1);
            }
            MessageResponseDto messageResponseDto = messageResponseConverter.toDto(messageRepository.save(entity));
            MessageActionDto messageActionDto = MessageActionDto.builder().
                    action(MessageActionTypeDto.CREATE).
                    data(messageResponseDto).
                    build();
            ProducerRecord<String, MessageActionDto> record = new ProducerRecord<>(messageChangeTopic, null,
                    System.currentTimeMillis(), String.valueOf(messageActionDto.toString()),
                    messageActionDto);
            kafkaMessageActionTemplate.send(record);
            return messageResponseDto;
        } else {
            throw new EntityExistsException(Messages.EntityExistsException);
        }
    }

    @Override
    public Optional<MessageResponseDto> read(@NonNull Long id) {
        return messageRepository.findMessageById(id).flatMap(author -> Optional.of(
                messageResponseConverter.toDto(author)));
    }

    @Override
    @Validated
    public MessageResponseDto update(@Valid @NonNull MessageRequestDto dto) throws NoEntityExistsException {
        Optional<Message> message = dto.getId() == null || messageRepository.findMessageByStoryIdAndId(
                dto.getStoryId(), dto.getId()).isEmpty() ?
                Optional.empty() : Optional.of(messageRequestConverter.fromDto(dto));
        MessageResponseDto messageResponseDto = messageResponseConverter.toDto(messageRepository.save(message.orElseThrow(() ->
                new NoEntityExistsException(Messages.NoEntityExistsException))));
        MessageActionDto messageActionDto = MessageActionDto.builder().
                action(MessageActionTypeDto.UPDATE).
                data(messageResponseDto).
                build();
        ProducerRecord<String, MessageActionDto> record = new ProducerRecord<>(messageChangeTopic, null,
                System.currentTimeMillis(), String.valueOf(messageActionDto.toString()),
                messageActionDto);
        kafkaMessageActionTemplate.send(record);
        return messageResponseDto;
    }

    @Override
    public Long delete(@NonNull Long id) throws NoEntityExistsException {
        Optional<Message> message = messageRepository.findMessageById(id);
        messageRepository.deleteMessageByStoryIdAndId(message.map(Message::getStoryId).orElseThrow(() ->
                new NoEntityExistsException(Messages.NoEntityExistsException)), message.map(Message::getId).
                orElseThrow(() -> new NoEntityExistsException(Messages.NoEntityExistsException)));
        MessageActionDto messageActionDto = MessageActionDto.builder().
                action(MessageActionTypeDto.DELETE).
                data(String.valueOf(id)).
                build();
        ProducerRecord<String, MessageActionDto> record = new ProducerRecord<>(messageChangeTopic, null,
                System.currentTimeMillis(), String.valueOf(messageActionDto.toString()),
                messageActionDto);
        kafkaMessageActionTemplate.send(record);
        return message.get().getId();
    }

    @Override
    public List<MessageResponseDto> readAll() {
        return collectionMessageResponseConverter.toListDto(messageRepository.findAll());
    }
}
