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

app.get('/', (req,res) => {
    res.render('login');
})

//9. Login
app.post("/login", async (req, res) => {
    const user = req.body.login;
    const password = req.body.password;
    let passwordHashed = await bcryptjs.hash(password, 8);
    connection.query(
        "INSERT INTO Usuario SET ?", {email:login, password:passwordHashed},
        async(error, results) => {
            if (error) {
                console.log(error);
            } else {
                console.log("El usuario se ha logueado correctamente");
            }
        }
    );
});

app.listen(3000, (req, res) => {
    console.log('El servidor está funcionando en http://localhost:3000');
})
