package by.teachmeskills.springbootproject.soap.repository;

import by.teachmeskills.springbootproject.soap.model.Nationality;
import by.teachmeskills.springbootproject.soap.model.Student;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;

@Component
public class StudentRepository {

    private static final Map<String, Student> students = new HashMap<>();

    @PostConstruct
    public void initData() {
        students.put("John", new Student("John", 2, 8.7, Nationality.AMERICA));
        students.put("Bob", new Student("Bob", 1, 7.4, Nationality.BRITAIN));
        students.put("Arhaan", new Student("Arhaan", 4, 9.5, Nationality.INDIA));
        students.put("Roma", new Student("Roma", 3, 8.3, Nationality.BELARUS));
    }

    public Student findStudent(String name) {
        return students.get(name);
    }
}