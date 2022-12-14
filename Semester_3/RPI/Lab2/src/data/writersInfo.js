import kupala from '../img/kupala/kupala.jpg';
import kupalaPhoto1 from '../img/kupala/kupalaPhoto1.jpg';
import kupalaPhoto2 from '../img/kupala/kupalaPhoto2.jpg';
import kupalaPhoto3 from '../img/kupala/kupalaPhoto3.jpg';

import kolas from '../img/kolas/kolas.jpg';
import kolasPhoto1 from '../img/kolas/kolasPhoto1.jpg';
import kolasPhoto2 from '../img/kolas/kolasPhoto2.jpg';
import kolasPhoto3 from '../img/kolas/kolasPhoto3.jpg';
import kolasPhoto4 from '../img/kolas/kolasPhoto4.jpg';
import kolasPhoto5 from '../img/kolas/kolasPhoto5.jpg';

import gilevich from '../img/gilevich/gilevich.jpg';
import gilevichPhoto1 from '../img/gilevich/gilevichPhoto1.jpg';
import gilevichPhoto2 from '../img/gilevich/gilevichPhoto2.jpg';
import gilevichPhoto3 from '../img/gilevich/gilevichPhoto3.jpg';
import gilevichPhoto4 from '../img/gilevich/gilevichPhoto4.jpg';
import gilevichPhoto5 from '../img/gilevich/gilevichPhoto5.jpg';

import bikov from '../img/bikov/bikov.jpg';
import bikovPhoto1 from '../img/bikov/bikovPhoto1.jpeg';
import bikovPhoto2 from '../img/bikov/bikovPhoto2.jpg';
import bikovPhoto3 from '../img/bikov/bikovPhoto3.jpg';
import bikovPhoto4 from '../img/bikov/bikovPhoto4.jpg';

import melezh from '../img/melezh/melezh.jpg';
import melezh1 from '../img/melezh/melezh1.jpg';
import melezh2 from '../img/melezh/melezh2.jpg';
import melezh3 from '../img/melezh/melezh3.jpg';

const writersInfo = [
    {
        id: 1,
        imgPath: kupala,
        name: "Янка Купала",
        name_en: "Yanka Kupala",
        dateOfBirth: 1882,
        dateOfDeath: 1942,
        someText: "Белорусский советский поэт и переводчик, драматург, публицист.\n" +
            "Окончил московский городской народный университет имени А.Л.Шанявского.\n" +
            "Настоящее имя - Иван Луцевич",
        photos: [
            kupalaPhoto1,
            kupalaPhoto2,
            kupalaPhoto3,
        ],
        links: [
            "https://www.youtube.com/embed/mk746fEHn4w",
            "https://www.youtube.com/embed/4yfl-cTWFX4"
        ],
        coordinates: {
            longitude: 27.19076,
            latitude: 54.11272
        },
        url: "/kupala"
    },
    {
        id: 2,
        imgPath: kolas,
        name: "Якуб Колас",
        name_en: "Yakub Kolas",
        dateOfBirth: 1882,
        dateOfDeath: 1956,
        someText:  "Белорусский писатель, драматург, поэт и переводчик, общественный деятель.\n" +
        "Один из классиков +и основоположников новой белорусской литературы.\n "+
        "Народный поэт Белорусской ССР.",
        photos: [
            kolasPhoto1,
            kolasPhoto2,
            kolasPhoto3,
            kolasPhoto4,
            kolasPhoto5
        ],
        links: [
            "https://www.youtube.com/embed/HxFeWGZspJQ",
            "https://www.youtube.com/embed/xHHd2ONkjuQ"
        ],
        coordinates: {
            longitude: 26.77895,
            latitude: 53.46443
        },
        url: "/kolas"
    },
    {
        id: 3,
        imgPath: gilevich,
        name: "Нил Гилевич",
        name_en: "Nil Hilevich",
        dateOfBirth: 1931,
        dateOfDeath: 2016,
        someText:  "Переводчик, литературовед, фольклорист, общественный деятель. Народный поэт Беларуси, Заслуженный деятель науки Белорусской ССР.\n" +
        "Лауреат Государственной премии Белорусской ССР имени Янки Купалы. Лауреат Международной премии имени Х. Ботева. Кандидат филологических наук, профессор. Член Союза писателей СССР.",
        photos: [
            gilevichPhoto1,
            gilevichPhoto2,
            gilevichPhoto3,
            gilevichPhoto4,
            gilevichPhoto5,
        ],
        links: [
            "https://www.youtube.com/embed/H_R5gvkA6Ks",
            "https://www.youtube.com/embed/j9FC-l66ymo"
        ],
        coordinates: {
            longitude: 27.70736,
            latitude: 54.27427
        },
        url: "/gilevich"
    },
    {
        id: 4,
        imgPath: bikov,
        name: "Василий Быков",
        name_en: "Vasiliy Bikov",
        dateOfBirth: 1924,
        dateOfDeath: 2003,
        someText: "Советский и белорусский писатель, общественный деятель.\n" +
            "Депутат Верховного Совета БССР 9—11 созывов, участник Великой Отечественной войны.\n" +
            "Член Союза писателей СССР.\n" +
            "Большинство произведений — повести, действие которых происходит во время Великой Отечественной войны\n" +
            "и в которых показан нравственный выбор человека в наиболее драматичные моменты жизни.",
        photos: [
            bikovPhoto1,
            bikovPhoto2,
            bikovPhoto3,
            bikovPhoto4
        ],
        links: [
            "https://www.youtube.com/embed/TT9Ezu0ZV4k",
            "https://www.youtube.com/embed/NSVN8B1wOfA"
        ],
        coordinates: {
            longitude: 28.384397,
            latitude: 55.165226
        },
        url: "/bikov"
    },
    {
        id: 5,
        imgPath: melezh,
        name: "Иван Мележ",
        name_en: "Ivan Melezh",
        dateOfBirth: 1921,
        dateOfDeath: 1976,
        someText:  "Народный писатель БССР (1972). Лауреат Литературной премии имени Якуба Коласа (1962).\n" +
            "Центральное место в его творчестве  занимает трилогия «Полесская хроника».\n" +
            "По произведениям И. Мележа поставлены спектакли, сняты художественные фильмы..",
        photos: [
            melezh1,
            melezh2,
            melezh3
        ],
        links: [
            "https://www.youtube.com/embed/I-0ezESiCCw",
            "https://www.youtube.com/embed/NwV8EoU_14M"
        ],
        coordinates: {
            longitude: 29.66563,
            latitude: 51.93467
        },
        url: "/melezh"
    },
];

export default writersInfo;