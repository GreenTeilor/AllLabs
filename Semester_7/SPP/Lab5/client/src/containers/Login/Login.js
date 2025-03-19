import './Login.css'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import {constants} from "../../utils/constants";
import {useState} from "react";

function Login({setActive}) {

    const [errorField, setErrorField] = useState(null);

    const handleLogin = async (e) => {
        e.preventDefault();
        const data = {
            email: e.target.email.value,
            password: e.target.password.value
        }
        try {
            const response = await fetch('/users/login', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            const responseData = await response.json();
            if (response.ok) {
                console.log('Successful login');
                localStorage.setItem('accessToken', responseData.accessToken);
                setActive(constants.appContainer);
            } else if (response.status === 400) {
                showError(responseData.message);
            }
            else {
                showError('Failed to login');
                console.error('Failed to login');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    const showError = (message) => {
        setErrorField(message);
        setTimeout(() => {
            setErrorField(null);
        }, 2000);
    }

    return (
        <div className="body">
            <h1 className="h1 text-center mb-4">Login</h1>

            <form onSubmit={handleLogin}>
                <div className="form-group">
                    <label htmlFor="email">Email address</label>
                    <input name="email" type="email" className="form-control" id="email"
                           placeholder="Enter email"/>
                </div>
                <div className="form-group">
                    <label htmlFor="password">Password</label>
                    <input name="password" type="password" className="form-control" id="password"
                           placeholder="Password"/>
                </div>
                <button type="submit" className="btn btn-primary loginBtn">Login</button>
                {errorField && <p className={"inputError"}>{errorField}</p>}
            </form>
            <div>
                <label className="toRegistrationLbl" htmlFor="toRegistrationBtn">Dont have an account? </label>
                <button id="toRegistrationBtn" className="btn btn-primary toRegistrationBtn"
                        onClick={() => {
                            setActive(constants.registrationContainer)
                        }}>To registration
                </button>
            </div>
            <div>
                <button id="toAppBtn" className="btn btn-primary toAppBtn"
                        onClick={() => {
                            setActive(constants.appContainer)
                        }}>To main page
                </button>
            </div>
        </div>
    );
}

export default Login;