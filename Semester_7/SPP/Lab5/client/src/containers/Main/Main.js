import App from "../App/App";
import Login from "../Login/Login";
import Registration from "../Registration/Registration";
import SwitchComponents from "../../components/SwitchComponents/SwitchComponents";
import React, {useState} from "react";
import {constants} from "../../utils/constants";

function Main() {

    const [active, setActive] = useState(constants.appContainer);

    return (
        <SwitchComponents active = {active}>
            <App name = {constants.appContainer} setActive = {setActive}/>
            <Login name = {constants.loginContainer} setActive = {setActive}/>
            <Registration name = {constants.registrationContainer} setActive = {setActive}/>
        </SwitchComponents>
    );
}

export default Main;