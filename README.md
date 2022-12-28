# Jeroboam Can Protocol

## Install dependencies
```
pip3 install yakut
```

```
pip3 install -U nunavut
```

## Compile DSDL for C/C++

```
nnvg --target-language c --target-endianness=little public_regulated_data_types/uavcan --outdir includes/
nnvg --target-language c --target-endianness=little public_regulated_data_types/reg --lookup-dir public_regulated_data_types/uavcan --outdir includes/
nnvg --target-language c --target-endianness=little jeroboam_datatypes/ --lookup-dir public_regulated_data_types/uavcan --outdir includes/
```

## Compile DSDL for Python

```
yakut compile public_regulated_data_types/uavcan/ public_regulated_data_types/reg/ jeroboam_datatypes/ -O includes/
```