const {Router} = require("express")
const controller = require("./controller")

const router = Router()

router.get("/", (req, res)=>{
    res.send("Using web-service.....")
}) 


router.get("/LoRa_Module/select_slave1", controller.select_slave1)
router.get("/LoRa_Module/select_slave2", controller.select_slave2)
router.get("/LoRa_Module/select_slave3", controller.select_slave3)
router.get("/LoRa_Module/select_slaveTest", controller.select_slaveTest)

router.post("/LoRa_Module/record", controller.record)
router.post("/LoRa_Module/test_record", controller.test_record)

router.get("/LoRa_Module/before1min_Slave1", controller.before1min_Slave1)
router.get("/LoRa_Module/before1min_Slave2", controller.before1min_Slave2)
router.get("/LoRa_Module/before1min_Slave3", controller.before1min_Slave3)


module.exports = router