import express from 'express';
import {Sequelize} from 'sequelize';
import path from 'path';
import bodyParser from 'body-parser';
import './src/entities/assosiations.js';
import {router} from './src/router/index.js';
import errorHandler from "./src/middlewares/errorHandler.js";

import {fileURLToPath} from 'url';
import {dirname} from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const app = express();
const port = 3000;

const sequelize = new Sequelize({
    dialect: 'sqlite',
    storage: './db/puzzles.db'
});

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));
app.use('/api/v1', router);
app.use(errorHandler);

app.listen(port, async () => {
    await sequelize.sync();
    console.log(`Server launched on http://localhost:${port}`);
});
