import {typeService} from "../services/TypeService.js";
import interceptor from "./ValidationInterceptor.js";

class TypeController {

    async getTypes(req, res, next) {
        try {
            const types = await typeService.getTypes();
            res.json(types);
        } catch (e) {
            next(e);
        }
    }

    async createType(req, res, next) {
        try {
            const {name} = req.body;
            const type = await typeService.createType({name});
            res.status(201);
            res.json(type);
        } catch (e) {
            next(e);
        }
    }
}

export const typeController = new TypeController();
interceptor.call(typeController, TypeController.prototype);