package by.bsuir.discussion.repositories;

import by.bsuir.discussion.domain.Message;
import org.springframework.data.cassandra.repository.AllowFiltering;
import org.springframework.data.cassandra.repository.MapIdCassandraRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface MessageRepository extends MapIdCassandraRepository<Message> {
    @AllowFiltering
    void deleteMessageByStoryIdAndId(Long id, Long uuid);
    @AllowFiltering //Bad solution, BUT generally we need to search all messages of certain story, so
                    //this search is redundant and that's why storyId is a partition key
    Optional<Message> findMessageById(Long id);
    Optional<Message> findMessageByStoryIdAndId(Long id, Long uuid);
}