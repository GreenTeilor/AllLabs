package by.bsuir.springbootproject.exceptions;

public class NoProductInInventoryException extends Exception {
    public NoProductInInventoryException(String message) {
        super(message);
    }
}
