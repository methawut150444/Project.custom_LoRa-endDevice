const pool = require('./db') 
const querise = require('./queries')

// ToDo: ______________________________________________________________________________________< Part: select each slave >
const select_slave1 = (req, res) => {
    pool.query(querise.select_slave1 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}
const select_slave2 = (req, res) => {
    pool.query(querise.select_slave2 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}
const select_slave3 = (req, res) => {
    pool.query(querise.select_slave3 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}
const select_slaveTest = (req, res) => {
    pool.query(querise.select_slaveTest , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}

// ToDo: ______________________________________________________________________________________< Part: select each slave amd time range >
const before1min_Slave1 = (req, res) => {
    console.log(req.body)
    pool.query(querise.before1min_Slave1 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}
const before1min_Slave2 = (req, res) => {
    console.log(req.body)
    pool.query(querise.before1min_Slave2 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}
const before1min_Slave3 = (req, res) => {
    console.log(req.body)
    pool.query(querise.before1min_Slave3 , (error, result) => {
        if (error) throw error;
        res.status(200).json(result.rows)
    })
}


// ToDo: ______________________________________________________________________________________< Part: record >
const record = (req, res) => {

    const {Slave, Data0, Data1, Data2, Data3, RSSI} = req.body
    // console.log(req.body)

    //Todo: generate current date & time
    const current_date = new Date().toLocaleDateString('en-CA', {timeZone: 'Asia/Bangkok'}).slice(0, 10)
    const current_time = new Date().toLocaleTimeString('en-US', {timeZone: 'Asia/Bangkok', hour12: false})
    if (current_time.startsWith("24")) {
        current_time = current_time.replace(/^24/, "00"); 
    }
    console.log(current_date)
    console.log(req.body)

    //Todo: record each slave
    if(Slave == 'node1'){
        //Todo: check last id
        pool.query(querise.checkLastID_Slave1, (error, result) => {
            if(Array.isArray(result.rows) && result.rows.length){  //Todo: ----- The first row have existed
                //Todo: record last id in table
                const id = result.rows[0].id + 1
                pool.query(querise.recordSlave1, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding NEW record in ${Slave} successfully.!`)
                })
            }
            else{                                                   //Todo: ----- The first row haven't exist
                //Todo: first record id: 0
                const id = 1
                pool.query(querise.recordSlave1, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding FIRST record in ${Slave} successfully.!`)
                })
            }
        })
    }
    else if(Slave == 'node2'){
        //Todo: check last id
        pool.query(querise.checkLastID_Slave2, (error, result) => {
            if(Array.isArray(result.rows) && result.rows.length){  //Todo: ----- The first row have existed
                //Todo: record last id in table
                const id = result.rows[0].id + 1
                pool.query(querise.recordSlave2, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding NEW record in ${Slave} successfully.!`)
                })
            }
            else{                                                   //Todo: ----- The first row haven't exist
                //Todo: first record id: 0
                const id = 1
                pool.query(querise.recordSlave2, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding FIRST record in ${Slave} successfully.!`)
                })
            }
        })
    }
    else if(Slave == 'node3'){
        //Todo: check last id
        pool.query(querise.checkLastID_Slave3, (error, result) => {
            if(Array.isArray(result.rows) && result.rows.length){  //Todo: ----- The first row have existed
                //Todo: record last id in table
                const id = result.rows[0].id + 1
                pool.query(querise.recordSlave3, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding NEW record in ${Slave} successfully.!`)
                })
            }
            else{                                                   //Todo: ----- The first row haven't exist
                //Todo: first record id: 0
                const id = 1
                pool.query(querise.recordSlave3, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                    if (error) throw error;
                    res.status(201).send(`Adding FIRST record in ${Slave} successfully.!`)
                })
            }
        })
    }

}

// ToDo: ______________________________________________________________________________________< Part: record (test) >
const test_record = (req, res) => {
    const {Slave, Data0, Data1, Data2, Data3, RSSI} = req.body
    // console.log(req.body)

    //Todo: generate current date & time
    const current_date = new Date().toLocaleDateString('en-CA', {timeZone: 'Asia/Bangkok'}).slice(0, 10)
    const current_time = new Date().toLocaleTimeString('en-US', {timeZone: 'Asia/Bangkok', hour12: false})
    if (current_time.startsWith("24")) {
        current_time = current_time.replace(/^24/, "00"); 
    }

    //Todo: check last id
    pool.query(querise.checkLastID_test, (error, result) => {
        if(Array.isArray(result.rows) && result.rows.length ){  //Todo: ----- The first row have existed
            //Todo: record last id in table
            const id = result.rows[0].id + 1
            pool.query(querise.test_record, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                if (error) throw error;
                res.status(201).send("Adding NEW record successfully.!")
            })
        }
        else{                                                   //Todo: ----- The first row haven't exist
            //Todo: first record id: 0
            const id = 1
            pool.query(querise.test_record, [id, current_date, current_time, Data0, Data1, Data2, Data3, RSSI], (error, result) => {
                if (error) throw error;
                res.status(201).send("Adding FIRST record successfully.!")
            })
        }
    })
}

module.exports = {
    select_slave1,
    select_slave2,
    select_slave3,
    select_slaveTest,

    before1min_Slave1,
    before1min_Slave2,
    before1min_Slave3,

    record,
    test_record,
} 