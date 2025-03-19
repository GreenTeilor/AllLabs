import './AddPuzzleForm.css'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import {authRequest} from "../../utils/authRequest";

function AddPuzzleForm({types, filter, setFilter, fetchPuzzles, showError, setActive}) {

    const handleAddPuzzle = async (e) => {
        e.preventDefault();
        const formData = new FormData();
        formData.append('name', e.target.name.value);
        formData.append('date', e.target.date.value);
        formData.append('type', e.target.type.value);
        formData.append('file', e.target.file.files[0]);
        try {
            const response = await authRequest(setActive,`/puzzles`, {
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

    return (
        <>
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
                            <option key={type.id} value={type.id} selected>{type.name}</option>
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
        </>
    )
}

export default AddPuzzleForm;
