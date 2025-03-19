import './App.css'
import {useEffect, useState} from "react";
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'

function App() {
    const domain = 'http://localhost:3000/'

    const [puzzles, setPuzzles] = useState([]);
    const [types, setTypes] = useState([]);
    const [filter, setFilter] = useState('all');
    const [isVisibleErrorField, setIsVisibleErrorField] = useState(false);

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

    const handleAddPuzzle = async (e) => {
        e.preventDefault();
        const formData = new FormData();
        formData.append('name', e.target.name.value);
        formData.append('date', e.target.date.value);
        formData.append('type', e.target.type.value);
        formData.append('file', e.target.file.files[0]);
        try {
            const response = await fetch('/puzzles', {
                method: 'POST',
                body: formData
            });

            if (response.ok) {
                console.log('Puzzle added successfully');
                setFilter('all');
                await fetchPuzzles(filter);
            } else {
                showError();
                console.error('Failed to add puzzle');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    const handleAddType = async (e) => {
        e.preventDefault();
        const data = {
            name: e.target.name.value
        }
        try {
            const response = await fetch('/types', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            if (response.ok) {
                console.log('Type added successfully');
                await fetchTypes();
            } else {
                showError();
                console.error('Failed to add type');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    const handlePuzzleChangeType = async(e) => {
        e.preventDefault();
        const data = {
            type: e.target.type.value
        }
        try {
            const puzzleId = e.target.puzzle.value;
            const response = await fetch(`/puzzles/${puzzleId}/type`, {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            if (response.ok) {
                console.log('Type changed successfully');
                await fetchPuzzles(filter);
            } else {
                showError();
                console.error('Failed to changed type');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    const showError = () => {
        setIsVisibleErrorField(true);
        setTimeout(() => {
            setIsVisibleErrorField(false);
        }, 2000);
    }

    return (
        <div className="body">

        <h1 className="h1 text-center mb-4">Puzzles</h1>

        <div className="container">
            <div className="row">

                <div className="col">
                    <h2 className="h2 mb-4">Add puzzle</h2>
                    <form onSubmit={handleAddPuzzle} className="addPuzzleForm">
                        <div className="mb-3">
                            <label form="puzzleName" className="form-label">Puzzle name</label>
                            <input type="text" name="name" placeholder="Puzzle name" className="form-control mr-2"
                                   id="puzzleName"
                                   required></input>
                        </div>
                        <div className="mb-3">
                            <label form="puzzleAddDate" className="form-label">Date</label>
                            <input type="date" name="date" className="form-control mr-2" id="puzzleAddDate"></input>
                        </div>
                        <div className="mb-3">
                            <label form="puzzleType" className="form-label">Type</label>
                            <select name="type" className="form-control mr-2" id="puzzleType">
                                {types.map(type => (
                                    <option key = { type.id } value={ type.id } selected>{ type.name }</option>
                                ))}
                            </select>
                        </div>
                        <div className="mb-3">
                            <label form="puzzleImage" className="form-label">Image</label>
                            <input className="form-control" type="file" name="file" id="puzzleImage"></input>
                        </div>
                        <div className="mb-3">
                            <button type="submit" className="btn btn-success mb-2">Add puzzle</button>
                        </div>
                    </form>

                    <h2 className="mb-4">Add type</h2>
                    <form onSubmit={handleAddType} className="addTypeForm">
                        <div className="mb-3">
                            <label form="typeName" className="form-label">Type name</label>
                            <input type="text" name="name" placeholder="Type name" className="form-control mr-2"
                                   id="typeName"
                                   required></input>
                        </div>
                        <div className="mb-3">
                            <button type="submit" className="btn btn-success mb-2">Add type</button>
                        </div>
                    </form>
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

                    <ul className="ul list-group mb-5">
                    {puzzles.map(puzzle => (
                            <li key = {puzzle.id} className="li list-group-item">
                                <div className="d-flex justify-content-between puzzle">
                                    <div>
                                        <p className="mb-1">Name: {puzzle.name}</p>
                                        <p className="mb-1">Type: {puzzle.Type.name}</p>
                                        <p className="mb-1">Date: {puzzle.date}</p>
                                        <img src={domain + 'img/' + puzzle.file} className="img-thumbnail" alt="Puzzle"
                                             width="100"
                                             height="100">
                                        </img>
                                        <a href={domain + 'img/' + puzzle.file} className="btn btn-info">Open image</a>
                                    </div>


                                    <form onSubmit={handlePuzzleChangeType} className="form-inline changePuzzleTypeForm">
                                        <input name="puzzle" hidden={true} value={puzzle.id}></input>
                                        <select name="type" className="custom-select mr-2">
                                            {types.map(type => (
                                                <option key={type.id} value={type.id}
                                                        selected={type.id === puzzle.Type.id}>
                                                    {type.name}
                                                </option>
                                            ))}
                                        </select>
                                        <button type="submit" className="btn btn-success">Update type</button>
                                    </form>
                                </div>
                            </li>
                        ))}
                    </ul>
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
