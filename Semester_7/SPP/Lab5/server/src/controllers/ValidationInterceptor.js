import {validationResult} from "express-validator";
import {ApiError} from "../exceptions/ApiError.js";

export default function intercept(prototype) {
    const ref = this;
    Object.getOwnPropertyNames(prototype).forEach((name) => {
        prototype['_' + name] = prototype[name];

        prototype[name] = function() {

            const req = arguments[0];
            const next = arguments[2];
            const errors = validationResult(req);
            if (!errors.isEmpty()) {
                return next(ApiError.BadRequest('Validation failed', errors.array()));
            }

            ref['_' + name](...arguments);
        };
    });
}