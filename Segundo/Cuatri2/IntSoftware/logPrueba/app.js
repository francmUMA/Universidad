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

console.log(__dirname);
app.get('/', (req,res) => {
    res.send('Hola Mundo');
})

app.listen(3000, (req, res) => {
    console.log('El servidor está funcionando en http://localhost:3000');
})
