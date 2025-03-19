import {Sequelize, DataTypes} from 'sequelize';
import express from 'express';
import path from 'path';
import multer from 'multer';
import bodyParser from 'body-parser';

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

const Type = sequelize.define('Type', {
    id: {
        type: DataTypes.INTEGER,
        primaryKey: true,
        autoIncrement: true
    },
    name: {
        type: DataTypes.STRING,
        allowNull: false
    }
}, {
    tableName: 'types',
    timestamps: false,
});

const Puzzle = sequelize.define('Puzzle', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        name: {
            type: DataTypes.STRING,
            allowNull: false
        },
        typeId: {
            type: DataTypes.INTEGER,
            allowNull: false,
            references: {
                model: Type,
                key: 'id'
            }
        },
        date: {
            type: DataTypes.STRING,
            allowNull: false
        },
        file: {
            type: DataTypes.STRING,
            allowNull: false
        }
    },
    {
        tableName: 'puzzles',
        timestamps: false,
    });

Puzzle.belongsTo(Type, {
    foreignKey: 'typeId',
    targetKey: 'id'
});
Type.hasMany(Puzzle, {
    foreignKey: 'typeId',
    sourceKey: 'id'
});

const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, 'public/img/');
    },
    filename: (req, file, cb) => {
        cb(null, Date.now() + '-' + file.originalname);
    }
});
const upload = multer({storage});


app.use(bodyParser.urlencoded({extended: true}));
app.use(express.static(path.join(__dirname, 'public')));
app.set('view engine', 'ejs');


app.get('/', async (req, res) => {
    const filter = req.query.filter || 'all';

    let whereClause = filter !== 'all' ? {typeId: filter} : {};

    const puzzles = await Puzzle.findAll({
        where: whereClause,
        include: {
            model: Type,
            attributes: ['id', 'name']
        }
    });

    const types = await Type.findAll();

    res.render('index', {puzzles, filter, types});
});


app.post('/add', upload.single('file'), async (req, res) => {
    const {name, date, type} = req.body;
    const file = req.file ? req.file.filename : null;

    await Puzzle.create({name, date, typeId: type, file});
    res.redirect('/');
});

app.post('/addType',async (req, res) => {
    const {name} = req.body;

    await Type.create({name});
    res.redirect('/');
});


app.post('/:id/type', async (req, res) => {
    const id = req.params.id;
    const type = req.body.type;

    let whereClause = {id: id}

    await Puzzle.update(
        {typeId: type},
        {where: whereClause}
    )
    res.redirect('/');
});


app.listen(port, async () => {
    await sequelize.sync();
    console.log(`Сервер запущен на http://localhost:${port}`);
});
