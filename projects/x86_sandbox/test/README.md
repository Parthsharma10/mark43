`test.dbc` tests the following:

- DBC code generated code
- Encodes and decodes CAN messages to ensure generate code is correct
  

The `test_dbc.c` operates on generated code from `test.dbc`

Steps:
```
# Generate/Update the `dbc.h` header file that we will test in `test.dbc`
python3 site_scons/site_tools/codegen/dbc_to_c.py --dbc site_scons/site_tools/codegen/tests/test.dbc --print-only > projects/x86_sandbox/dbc.h

# Run the tests as usual
scons --project=x86_sandbox
```

