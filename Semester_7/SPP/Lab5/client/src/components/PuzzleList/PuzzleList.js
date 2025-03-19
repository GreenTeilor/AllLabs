import './PuzzleList.css'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import {authRequest} from "../../utils/authRequest";

function PuzzleList({domain, puzzles, fetchPuzzles, types, setActive, socket}) {

    const handlePuzzleChangeType = async (e) => {
        e.preventDefault();
        const data = {
            type: e.target.type.value
        }
        try {
            const puzzleId = e.target.puzzle.value;
            const response = await authRequest(setActive, `/puzzles/${puzzleId}/type`, {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            if (response.ok) {
                console.log('Type changed successfully');
                fetchPuzzles(data.type);
            } else {
                console.error('Failed to changed type');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    const deletePuzzle = async (e) => {
        e.preventDefault();
        try {
            const puzzleId = e.target.puzzle.value;
            const query = `
                mutation($id: ID) {
                    deletePuzzle(id: $id) {
                        id,
                        name
                    }
                }
            `;
            const variables = {
                id: puzzleId
            };
            const data = {
                query,
                variables
            }
            const response = await authRequest(setActive, `/graphql`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            if (response.ok) {
                console.log('Puzzle deleted successfully');
                socket.emit('puzzleDeletedEvent', puzzleId);
            } else {
                console.error('Failed to delete puzzle');
            }
        } catch (error) {
            console.error('Error:', error);
        }
    }

    return (
        <ul className="ul list-group mb-5">
            {puzzles.map(puzzle => (
                <li key={puzzle.id} className="li list-group-item">
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

                        <div>
                            <form onSubmit={deletePuzzle} className="form-inline deletePuzzleForm">
                                <input name="puzzle" hidden={true} value={puzzle.id}></input>
                                <input name="type" hidden={true} value={puzzle.Type.id}></input>
                                <button type="submit" className="btn btn-close"></button>
                            </form>
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
                    </div>
                </li>
            ))}
        </ul>
    )
}

export default PuzzleList;
