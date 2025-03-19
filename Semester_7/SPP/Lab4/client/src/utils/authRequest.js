import {jwtDecode} from "jwt-decode";
import {constants} from "./constants";

//Return true if update by refresh token was redundant or successful, false otherwise
async function updateTokensIfAccessExpired() {
    const possibleAccessToken = localStorage.getItem('accessToken');
    if (possibleAccessToken && (Date.now() / 1000 >= jwtDecode(possibleAccessToken).exp)) {
        const response = await fetch('/users/refresh', {
            method: 'POST',
            credentials: 'include'
        });
        if (response.status === 401) {
            return false;
        } else {
            const data = await response.json();
            localStorage.setItem('accessToken', data.accessToken);
        }
    }
    return true;
}

//setActive - function from useState hook to switch components
export async function authRequest(setActive, url, options = {}) {
    if (!(await updateTokensIfAccessExpired())) {
        setActive(constants.loginContainer);
    }

    const headers = {
        ...options.headers,
        'Authorization': `Bearer ${localStorage.getItem('accessToken')}`,
        credentials: 'include'
    };

    const response = await fetch(url, {
        ...options,
        headers
    });

    if (response.status === 401) {
        setActive(constants.loginContainer);
    }
    return response;
}