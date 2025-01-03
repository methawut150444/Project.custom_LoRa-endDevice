const {Pool} = require('pg')

const pool = new Pool({
    host: "localhost",
    user: "postgres",
    port: 5432,
    password: "por150444",
    database: "IndependentStudy_LoRa"
})

module.exports = pool


