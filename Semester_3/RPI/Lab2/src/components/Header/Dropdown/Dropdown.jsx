import React from 'react';
import Globe from "../Globe/Globe";
import i18next from "i18next";
import s from './Dropdown.module.css'

const Dropdown = (props) => {
    return (
        <div className={s.wrapper}>
            <div className={s.dropdown}>
                <button className="btn btn-link dropdown-toggle" type="button" data-bs-toggle="dropdown"
                        aria-expanded="false">
                    <Globe />
                </button>
                <ul className="dropdown-menu">
                    {props.languages.map(({code, name, country_code}) => (
                        <li key={country_code}>
                            <button className="dropdown-item" onClick={() => i18next.changeLanguage(code)}>
                                <span className={`flag-icon flag-icon-${country_code} mx-2`}> </span>
                                {name}
                            </button>
                        </li>
                    ))}
                </ul>
            </div>
        </div>
    );
};

export default Dropdown;