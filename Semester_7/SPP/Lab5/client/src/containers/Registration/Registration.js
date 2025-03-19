import './Registration.css'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import {constants} from "../../utils/constants";
import {useState} from "react";

function Registration({setActive}) {

    const [errorField, setErrorField] = useState(null);

    const handleRegistration = async (e) => {
        e.preventDefault();
        const data = {
            email: e.target.email.value,
            password: e.target.password.value
        }
        try {
            const response = await fetch('/users/register', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            const responseData = await response.json();
            if (response.ok) {
                console.log('Successful registration');
                localStorage.setItem('accessToken', responseData.accessToken);
                setActive(constants.appContainer);
            } else if (response.status === 400) {
                showError(responseData.message);
            }
            else {
                showError('Registration failed');
                console.error('Registration failed');
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
            <h1 className="h1 text-center mb-4">Registration</h1>

            <form onSubmit={handleRegistration}>
                <div className="form-group">
                    <label htmlFor="email">Email address</label>
                    <input name="email" type="email" className="form-control" id="email" aria-describedby="emailHelp"
                           placeholder="Enter email"/>
                </div>
                <div className="form-group">
                    <label htmlFor="password">Password</label>
                    <input name="password" type="password" className="form-control" id="password"
                           placeholder="Password"/>
                </div>
                <button type="submit" className="btn btn-primary loginBtn">Register</button>
                {errorField && <p className={"inputError"}>{errorField}</p>}
            </form>
            <div>
                <label className="toLoginLbl" htmlFor="toRegistrationBtn">Already have an account? </label>
                <button id="toRegistrationBtn" className="btn btn-primary toLoginBtn"
                        onClick={() => {
                            setActive(constants.loginContainer)
                        }}>To login
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

export default Registration;