package by.bsuir.publisher.repositories;

import by.bsuir.publisher.domain.Message;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface MessageCacheRepository extends CrudRepository<Message, Long> {
}
