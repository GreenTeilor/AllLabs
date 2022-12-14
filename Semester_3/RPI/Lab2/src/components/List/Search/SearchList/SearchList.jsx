import React from 'react';
import Card from '../Card/Card';
import s from "./SearchList.module.css"

function SearchList(props) {
    return (
        <div className={s.writers}>
            {props.filteredPersons.map((person, i) => <Card key={i} person={person} />)}
        </div>
    );
}

export default SearchList;