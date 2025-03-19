import Router from 'express';
import {puzzleController} from "../controllers/PuzzleController.js";
import {typeController} from "../controllers/TypeController.js";
import {userController} from "../controllers/UserController.js";
import {body} from 'express-validator';
import {query} from 'express-validator';
import {param} from 'express-validator';
import multer from "multer";
import {ApiError} from "../exceptions/ApiError.js";
import authHandler from "../middlewares/authHandler.js";

export const router = new Router();

const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, 'public/img/');
    },
    filename: (req, file, cb) => {
        cb(null, Date.now() + '-' + file.originalname);
    }
});
const upload = multer({storage});

router.get('/puzzles',
    query('filter').notEmpty().withMessage('Filter can\'t be empty'),
    puzzleController.getPuzzles);

router.get('/types',
    typeController.getTypes);

router.route('/puzzles').post(upload.single('file'),
    authHandler,
    body('file')
        .custom((value, { req}) => {
                            if (!req.file) {
                                throw new ApiError.BadRequest('Validation failed')
                            }
                            return true;
        }).withMessage('File can\'t be empty'),
    body('name')
        .notEmpty().withMessage('Name can\'t be empty')
        .matches(/^(?!\s*$).+/).withMessage('Name has to contain at least one non-space character'),
    body('date')
        .notEmpty().withMessage('Date can\'t be empty')
        .isDate().withMessage('Invalid date format'),
    body('type')
        .notEmpty().withMessage('Type can\'t be empty')
        .isNumeric().withMessage('Type has to be numeric'),
    puzzleController.createPuzzle);

router.post('/types',
    authHandler,
    body('name')
        .notEmpty().withMessage('Name can\'t be empty')
        .matches(/^(?!\s*$).+/).withMessage('Name has to contain at least one non-space character'),
    typeController.createType);

router.put('/puzzles/:id/type',
    authHandler,
    param('id')
        .notEmpty().withMessage('Id can\'t be empty')
        .isNumeric().withMessage('Id has to be numeric'),
    body('type')
        .notEmpty().withMessage('Type can\'t be empty')
        .isNumeric().withMessage('Type has to be numeric'),
    puzzleController.updatePuzzleType);

router.post('/users/register',
    body('email')
        .isEmail().withMessage('Wrong email format'),
    body('password')
        .matches(/^.{3,}$/).withMessage("Password has to contain at least 3 characters"),
    userController.register);

router.post('/users/login',
    body('email')
        .isEmail().withMessage('Wrong email format'),
    body('password')
        .matches(/^.{3,}$/).withMessage("Password has to contain at least 3 characters"),
    userController.login);

router.post('/users/logout',
    authHandler,
    userController.logout);

router.post('/users/refresh', userController.refresh);

router.get('/users/activate/:link',
    param('link')
        .notEmpty().withMessage('Name can\'t be empty'),
    userController.activate);