package by.teachmeskills.springbootproject.soap;

import by.teachmeskills.springbootproject.soap.model.GetStudentRequest;
import by.teachmeskills.springbootproject.soap.model.GetStudentResponse;
import by.teachmeskills.springbootproject.soap.repository.StudentRepository;
import lombok.AllArgsConstructor;
import org.springframework.ws.server.endpoint.annotation.Endpoint;
import org.springframework.ws.server.endpoint.annotation.PayloadRoot;
import org.springframework.ws.server.endpoint.annotation.RequestPayload;
import org.springframework.ws.server.endpoint.annotation.ResponsePayload;

@Endpoint
@AllArgsConstructor
public class StudentEndpoint {

    private static final String NAMESPACE_URI = "https://www.baeldung.com/springsoap/gen";

    private StudentRepository studentRepository;

    @PayloadRoot(namespace = NAMESPACE_URI, localPart = "getStudentRequest")
    @ResponsePayload
    public GetStudentResponse getStudent(@RequestPayload GetStudentRequest request) {
        GetStudentResponse response = new GetStudentResponse();
        response.setStudent(studentRepository.findStudent(request.getName()));

        return response;
    }
}
