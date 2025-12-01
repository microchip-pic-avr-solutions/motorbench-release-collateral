# Release Collateral for motorBench® Development Suite + Custom Board Files

## Custom Board Files

The **`custom-board-files/`** directory contains **additional reference examples** for defining custom hardware platforms.

These include example configurations for boards such as:

- **MCHV-230V / 1.5 kW custom board**
- **Multi-Phase Power Board using dsPIC33CK**
- **Other experimental or contributed board definitions**

These files show how to structure advanced or specialized board definitions for motorBench® and can be used as templates or inspiration when creating your own YAML configurations.

---

## Disclaimer

The custom board files in this repository are:

- **not fully tested**,  
- **not validated**,  
- **not officially supported**,  
- and provided **as-is**.

They are intended **only as helpful reference material**, similar to the community-driven examples found in open-source ecosystems.

There is **no guarantee** that these configurations will work out-of-the-box on your hardware.  
They may require modification, adaptation, or debugging depending on your specific application.

**Use at your own risk.**

---


## Included Projects and Files

1. **sample-mb-33ep256mc506-mclv2.X**  
   motorBench® project for **dsPIC33EP256MC506 External Op Amp PIM + MCLV-2** development board

2. **sample-mb-33ep256mc506-mchv2.X**  
   motorBench® project for **dsPIC33EP256MC506 External Op Amp PIM + MCHV-2 / MCHV-3** development boards

3. **zsmt-reference-actblf02-lvmc.X**  
   Reference project demonstrating the **ZS/MT hybrid estimator** using the **ACT 57BLF02** motor

4. **zsmt-reference-elra-lvmc.X**  
   Reference project demonstrating the **ZS/MT hybrid estimator** using the **ELRA IPM80S-24V** motor

5. **zsmt-reference-linix-lvmc.X**  
   Reference project demonstrating the **ZS/MT hybrid estimator** using the **Linix 45ZWN24-40** motor

6. **mcc-manifest-autosave.yml**  
   MCC manifest file that can be loaded in MCC Content Manager to ensure the same tested content versions are used

7. **motorBench-2.50.0-Release-Notes.pdf**  
   Official motorBench® release notes

8. **motorBench-2.50.0-Users-Guide.pdf**  
   Official motorBench® user guide

9. **starter-board.yaml**  
   A minimal board-definition template — an ideal starting point for creating a new **custom board**.


---
