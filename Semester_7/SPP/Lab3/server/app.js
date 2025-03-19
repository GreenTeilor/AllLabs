import express from 'express';
import {sequelize} from './src/repositories/sequelize.js';
import path from 'path';
import bodyParser from 'body-parser';
import './src/entities/assosiations.js';
import {router} from './src/router/index.js';
import errorHandler from "./src/middlewares/errorHandler.js";
import cookieParser from "cookie-parser";
import cors from "cors";
import dotenv from "dotenv";

import {fileURLToPath} from 'url';
import {dirname} from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));
app.use(cookieParser());
app.use(cors());
app.use('/api/v1', router);
app.use(errorHandler);
dotenv.config();

app.listen(port, async () => {
    await sequelize.sync();
    console.log(`Server launched on http://localhost:${port}`);
});
