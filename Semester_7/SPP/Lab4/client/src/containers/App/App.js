import './App.css'
import {useEffect, useState} from "react";
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import PuzzleList from "../../components/PuzzleList/PuzzleList";
import AddPuzzleForm from "../../components/AddPuzzleForm/AddPuzzleForm";
import AddTypeForm from "../../components/AddTypeForm/AddTypeForm";
import io from 'socket.io-client';
import Notification from "../../components/Notification/Notification";
import {constants} from "../../utils/constants";

const socket = io(constants.domain);

function App({setActive}) {

    const [puzzles, setPuzzles] = useState([]);
    const [types, setTypes] = useState([]);
    const [filter, setFilter] = useState('all');
    const [isVisibleErrorField, setIsVisibleErrorField] = useState(false);
    const [notificationQueue, setNotificationQueue] = useState([]);

    useEffect(() => {
        socket.on('puzzleAddedEvent', (msg) => {
            addNotification(msg)
        });

        socket.on('typeAddedEvent', (msg) => {
            addNotification(msg)
        });

        return () => {
            socket.off('puzzleAddedEvent');
            socket.off('typeAddedEvent');
        };
    }, []);

    useEffect(() => {
        fetchPuzzles(filter);
    }, [filter]);

    useEffect(() => {
        fetchTypes();
    }, []);

    const fetchPuzzles = async (filter) => {
        try {
            const response = await fetch(`/puzzles?filter=${encodeURIComponent(filter)}`);
            const data = await response.json();
            setPuzzles(data);
        } catch (error) {
            console.error('Error fetching puzzles:', error);
        }
    }

    const fetchTypes = async () => {
        try {
            const response = await fetch(`/types`);
            const data = await response.json();
            setTypes(data);
        } catch (error) {
            console.error('Error fetching types:', error);
        }
    }

    const showError = () => {
        setIsVisibleErrorField(true);
        setTimeout(() => {
            setIsVisibleErrorField(false);
        }, 2000);
    }

    const addNotification = (body) => {
        notificationQueue.unshift(body);
        setNotificationQueue([...notificationQueue]);
        setTimeout(() => {
            notificationQueue.pop();
            setNotificationQueue([...notificationQueue]);
        }, 2000);
    }

    return (
        <div className="body">

        <h1 className="h1 text-center mb-4">Puzzles</h1>

        <div className="container">
            <div className="row">

                <div className="col">
                    <AddPuzzleForm types={types} filter={filter} setFilter={setFilter} fetchPuzzles={fetchPuzzles} showError={showError} setActive={setActive} socket={socket}/>

                    <AddTypeForm fetchTypes={fetchTypes} showError={showError} setActive={setActive} socket={socket}/>
                    {isVisibleErrorField && <p className={"inputError"}>Incorrect input fields!</p>}
                </div>

                <div className="col">

                    <h2 className="mb-4">Info</h2>
                    <div className="mb-4 filter">
                        {types.map(type => (
                            <button key = {type.id} onClick={() => setFilter(type.id)} className="btn btn-info">{type.name}</button>
                        ))}
                        <button onClick={() => setFilter('all')} className="btn btn-info">All</button>
                    </div>

                    <PuzzleList domain={constants.domain} puzzles={puzzles} fetchPuzzles={fetchPuzzles} types={types} setActive={setActive}/>

                    <div className="notifications">
                        {notificationQueue.map(notification => (
                            <Notification body={notification} />
                        ))}
                    </div>
                </div>

            </div>
        </div>

        <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.5.2/dist/umd/popper.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
        </div>
    )
}

export default App;
