import './Notification.css'

function Notification({ body }) {

    return (
        <div className="div">
            <div dangerouslySetInnerHTML={{ __html: body }} />
        </div>
    );
}

export default Notification;