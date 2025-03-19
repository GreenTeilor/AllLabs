import './AddTypeForm.css'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'jquery/dist/jquery.min.js'
import 'bootstrap/dist/js/bootstrap.min.js'
import {authRequest} from "../../utils/authRequest";

function AddTypeForm({fetchTypes, showError, setActive}) {

    const handleAddType = async (e) => {
        e.preventDefault();
        const data = {
            name: e.target.name.value
        }
        try {
            const response = await authRequest(setActive,'/types', {
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

    return (
        <>
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
        </>
    )
}

export default AddTypeForm;
