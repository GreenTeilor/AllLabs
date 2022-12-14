import React from 'react';
import PortalInfo from "./Portal/PortalInfo";
import MainPerson from "./MainPerson/MainPerson";
import DevelopersInfo from "./Developers/DevelopersInfo";
import developersInfo from "../../data/developersInfo";

const Info = (props) => {
    return (
        <div>
            <PortalInfo />
            <MainPerson person={props.mainPerson}/>
            <DevelopersInfo info={developersInfo}/>
        </div>
    );
};

export default Info;