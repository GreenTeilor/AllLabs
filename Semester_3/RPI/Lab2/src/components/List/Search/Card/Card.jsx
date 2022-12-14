import React from 'react';
import s from "./Card.module.css"
import {NavLink} from "react-router-dom";
import {useTranslation} from "react-i18next";

function Card(props) {
    const {t} = useTranslation();
    const name = props.person.name_en.toLowerCase().split(' ').join('_');
    return(
        <div className={s.writer}>
            <NavLink to={props.person.url}><img alt="" src={props.person.imgPath}/></NavLink>
            <h2>{t(name)}</h2>
        </div>
    );
}

export default Card;