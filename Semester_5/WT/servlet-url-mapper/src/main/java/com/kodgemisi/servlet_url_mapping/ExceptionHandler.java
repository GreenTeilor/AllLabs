package com.kodgemisi.servlet_url_mapping;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

/**
 * Handles any exception during doXXX methods of {@link MappingServlet}. {@link MappingServlet} uses
 * {@link LoggingExceptionHandler} as default implementation.
 *
 * @see LoggingExceptionHandler
 */
@FunctionalInterface
public interface ExceptionHandler {

    void handleException(HttpServletRequest request, HttpServletResponse response, Exception e);

}
