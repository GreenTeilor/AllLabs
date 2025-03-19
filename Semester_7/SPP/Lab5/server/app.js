import express from 'express';
import {graphqlHTTP} from "express-graphql";
import schema from './src/schema/schema.js';
import {sequelize} from './src/repositories/sequelize.js';
import path from 'path';
import bodyParser from 'body-parser';
import './src/entities/assosiations.js';
import {router} from './src/router/index.js';
import errorHandler from "./src/middlewares/errorHandler.js";
import cookieParser from "cookie-parser";
import cors from "cors";
import dotenv from "dotenv";
import http from "http";
import {Server} from "socket.io";

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
app.use('/graphql', graphqlHTTP({
    schema,
    graphiql: true,
}));
app.use(errorHandler);
dotenv.config();

const server = http.createServer(app);
const io = new Server(server, {
    cors: {
        origin: process.env.CLIENT_URL
    }
});

io.on('connection', (socket) => {
    console.log('User connected');

    socket.on('puzzleAddedEvent', (msg) => {
        io.emit('puzzleAddedEvent', msg);
    });

    socket.on('typeAddedEvent', (msg) => {
        io.emit('typeAddedEvent', msg);
    });

    socket.on('puzzleDeletedEvent', (msg) => {
        io.emit('puzzleDeletedEvent', msg);
    });

    socket.on('typeDeletedEvent', (msg) => {
        io.emit('typeDeletedEvent', msg);
    });

    socket.on('disconnect', () => {
        console.log('User disconnected');
    });
});

server.listen(port, async () => {
    await sequelize.sync();
    console.log(`Server launched on http://localhost:${port}`);
});
