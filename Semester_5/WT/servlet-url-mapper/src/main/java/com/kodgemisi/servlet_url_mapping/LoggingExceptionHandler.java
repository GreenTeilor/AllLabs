package com.kodgemisi.servlet_url_mapping;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * Logs and rethrows any uncaught exception wrapped in a RuntimeException.
 */
public class LoggingExceptionHandler implements ExceptionHandler {

    private static final Logger log = LoggerFactory.getLogger(LoggingExceptionHandler.class);

    @Override
    public void handleException(HttpServletRequest request, HttpServletResponse response, Exception e) {
        log.error(e.getMessage(), e);
        throw new RuntimeException(e);
    }
}
