import {ApiError} from "../exceptions/ApiError.js";
import {SqlError} from "../exceptions/SqlError.js";

export default function errorHandler(err, req, res, next) {
    if (err instanceof ApiError) {
        return res.status(err.status).json({
            message: err.message,
            errors: err.errors
        })
    } else if (err instanceof SqlError) {
        return res.status(500).json({
            message: err.message
        })
    }
    return res.status(500).json({
        message: 'Unexpected server error'
    })
}