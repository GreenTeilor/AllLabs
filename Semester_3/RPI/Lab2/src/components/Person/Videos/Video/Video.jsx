import React from 'react';
import s from './Video.module.css'

const Video = (props) => {
    return (
        <div className="ratio ratio-16x9">
            <iframe src={props.link} title="YouTube video" allowFullScreen> </iframe>
        </div>
    );
};

export default Video;