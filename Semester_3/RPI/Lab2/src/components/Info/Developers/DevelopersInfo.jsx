import React from 'react';
import Developer from "./Developer/Developer"
import s from "./DevelopersInfo.module.css"
import {useTranslation} from "react-i18next";

const DevelopersInfo = (props) => {
    const {t} = useTranslation();
    return (
        <div className={s.wrapper}>
            <h1>{t('developers')}</h1>
            <div className={s.list}>
                {props.info.map((info, i) => <Developer key={i} info={info}/>)}
            </div>
        </div>
    );
}

export default DevelopersInfo;