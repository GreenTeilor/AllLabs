import React from 'react';
import s from "./List.module.css";
import Search from "./Search/Search";
import writersInfo from "../../data/writersInfo.js";

const List = (props) => {
    return (
        <div className={s.wrapper}>
            <Search details={writersInfo}/>
        </div>
    );
};

export default List;