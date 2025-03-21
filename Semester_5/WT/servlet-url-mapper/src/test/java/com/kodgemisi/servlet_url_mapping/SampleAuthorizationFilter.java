package com.kodgemisi.servlet_url_mapping;

import jakarta.servlet.Filter;
import jakarta.servlet.FilterChain;
import jakarta.servlet.FilterConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

/**
 * Created on October, 2018
 *
 * @author destan
 */
class SampleAuthorizationFilter implements Filter {

	private final ServletUrlPattern servletUrlPattern;

	SampleAuthorizationFilter() {
		this(true);
	}

	SampleAuthorizationFilter(boolean useTrailingSlashMatch) {
		servletUrlPattern = new ServletUrlPattern(useTrailingSlashMatch);
		servletUrlPattern.register("admin", "/admin/.*");
		servletUrlPattern.register("logout", "/logout");
	}

	@Override
	public void init(FilterConfig filterConfig) {
	}

	@Override
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		final ServletUrl result = servletUrlPattern.parse((HttpServletRequest) request);
		switch (result.getName()) {
			case "admin":
				if (!isCurrentUserAdmin()) {
					((HttpServletResponse) response).sendError(HttpServletResponse.SC_FORBIDDEN);
					return;
				}
				break;

			case "logout":
				preLogoutWork();
				break;
		}

		chain.doFilter(request, response);
	}

	@Override
	public void destroy() {

	}

	boolean isCurrentUserAdmin() {
		//do some work
		return true;
	}

	void preLogoutWork() {
		//do some work
	}
}
