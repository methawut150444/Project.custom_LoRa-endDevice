const select_slave1 = `SELECT * FROM "slave1" ORDER BY id ASC`
const select_slave2 = `SELECT * FROM "slave2" ORDER BY id ASC`
const select_slave3 = `SELECT * FROM "slave3" ORDER BY id ASC`
const select_slaveTest = `SELECT * FROM "test_record" ORDER BY id ASC`

const recordSlave1 = `insert into "slave1" (id, date, time, data0, data1, data2, data3, rssi) values($1, $2, $3, $4, $5, $6, $7, $8)`
const recordSlave2 = `insert into "slave2" (id, date, time, data0, data1, data2, data3, rssi) values($1, $2, $3, $4, $5, $6, $7, $8)`
const recordSlave3 = `insert into "slave3" (id, date, time, data0, data1, data2, data3, rssi) values($1, $2, $3, $4, $5, $6, $7, $8)`
const checkLastID_Slave1 = `SELECT * FROM "slave1" ORDER BY id DESC limit 1`
const checkLastID_Slave2 = `SELECT * FROM "slave2" ORDER BY id DESC limit 1`
const checkLastID_Slave3 = `SELECT * FROM "slave3" ORDER BY id DESC limit 1`

const test_record = `insert into "test_record" (id, date, time, data0, data1, data2, data3, rssi) values($1, $2, $3, $4, $5, $6, $7, $8)`
const checkLastID_test = `SELECT * FROM "test_record" ORDER BY id DESC limit 1`

const before1min_Slave1 = `SELECT * FROM slave1 ORDER BY id Desc limit 6`
const before1min_Slave2 = `SELECT * FROM slave2 ORDER BY id Desc limit 6`
const before1min_Slave3 = `SELECT * FROM slave3 ORDER BY id Desc limit 6`

module.exports = {
    select_slave1,
    select_slave2,
    select_slave3,

    recordSlave1,
    recordSlave2,
    recordSlave3,
    checkLastID_Slave1,
    checkLastID_Slave2,
    checkLastID_Slave3,

    select_slaveTest,
    test_record,
    checkLastID_test,

    before1min_Slave1,
    before1min_Slave2,
    before1min_Slave3,
}