import i18n from "i18next";
import {initReactI18next} from "react-i18next";
import LanguageDetector from 'i18next-browser-languagedetector';
import Backend from 'i18next-http-backend';
import translationEN from './translations/translationEN.json'
import translationRU from './translations/translationRU.json';

i18n.use(Backend).use(LanguageDetector).use(initReactI18next).init({
    resources: {
        en: {
            translation: translationEN
        },
        ru: {
            translation: translationRU
        }
    },
    fallbackLng: "ru",
    lng: "ru",
});

export default i18n;