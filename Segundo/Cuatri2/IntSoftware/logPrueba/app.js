// 1. Inicializar express
const express = require('express');
const app = express();                  //usar los metodos de express

//2. Captura de datos de formulario
app.use(express.urlencoded({extended:false}));
app.use(express.json());

//3. Inicializar dotenv
const dotenv = require('dotenv');
dotenv.config({path: './env/.env'});

//4. Configurar el directorio public
app.use('/resources', express.static('public'));
app.use('/resources', express.static(__dirname + '/public'));

//5. Establecer el motor de plantillas
app.set('view engine', 'ejs');

//6. Configurar el cifrado de contraseñas
const bcryptjs = require('bcryptjs');

//7. Variables de sesion
const session = require('express-session');
app.use(session({
    secret: 'secret',
    resave: true,
    saveUninitialized: true
}))

//8. Inicializar la conexion a la base de datos
const connection = require('./database/db');

//9. Establecer ruta de las plantillas
app.get('/', (req,res) => {
    res.render('index', {user: "Loading..."});
})

app.get('/login', (req,res) => {
    res.render('login');
})

app.get('/register', (req,res) => {
    res.render('register');
})

//10. Registro
app.post('/register', async (req, res) => {
    const user = req.body.user;
    const password = req.body.password;
    let passHashed = await bcryptjs.hash(password, 8);
    connection.query(
        "INSERT INTO Usuario SET ?",
        {email:user, password:passHashed},
        async(error, results) => {
            if (error) {
               console.log(error);
            } else {
                res.render('index', {user:user});
            }
        }
    )
});
//618 986 446
//11. Login
app.post('/auth', async (req, res) => {
    const user = req.body.user;
    const password = req.body.password;
    let passHashed = await bcryptjs.hash(password, 8);
    if (user && password){
        connection.query(
            "SELECT * FROM Usuario WHERE email = ?", [user],
            async (error, results) => {
                if (results.length == 0 || !(await bcryptjs.compare(password, results[0].password))){
                    res.send('El usuario o la contraseña introducidas no es correcta');
                } else {
                    console.log("Login exitoso");
                    res.render('index', {user: user});
                }
        })
    }
})

app.listen(3000, (req, res) => {
    console.log('El servidor está funcionando en http://localhost:3000');
})
