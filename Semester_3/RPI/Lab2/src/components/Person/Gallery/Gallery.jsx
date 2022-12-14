import React, {useState} from 'react';
import s from './Gallery.module.css'
import CloseIcon from '@mui/icons-material/Close';
import {useTranslation} from "react-i18next";

const Gallery = (props) => {
    const {t} = useTranslation();
    const [model, setModel] = useState(false);
    const [tempImgSrc, setTempImgSrc] = useState('');
    const getImg = (imgSrc) => {
        setTempImgSrc(imgSrc);
        setModel(true);
    }
    return (
        <>
            <h1>{t('gallery')}</h1>
            <div className={model ? `${s.model} ${s.open}` : s.model}>
                <img src={tempImgSrc} alt=""/>
                <CloseIcon onClick={() => setModel(false)}/>
            </div>
            <div className={s.gallery}>
                {props.photos.map((imgSrc, i) => {
                    let width = '100%';
                    return (
                        <div className={s.pics} key={i} onClick={() => getImg(imgSrc)}>
                            <img src={imgSrc} alt="" style={{width: width}}/>
                        </div>
                    )
                })}
            </div>
        </>
    );
};

export default Gallery;