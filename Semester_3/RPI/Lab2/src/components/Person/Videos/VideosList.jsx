import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import { Container } from 'react-bootstrap'
import Video from "./Video/Video";
import s from './VideoList.module.css'
import {useTranslation} from "react-i18next";

const VideosList = (props) => {
    const {t} = useTranslation();
    return (
        <div className={s.wrapper}>
            <h1>{t('videos')}</h1>
            <Container className={s.videos}>
                {props.links.map((link, i) => <Video key={i} link={link}/>)}
            </Container>
        </div>
    );
};

export default VideosList;