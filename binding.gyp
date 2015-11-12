{
  "targets": [
    {
      "target_name": "bcm2835-io",
      "sources": [
        "src/bcm2835-io.cc",
        "src/bcm2835.c"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

