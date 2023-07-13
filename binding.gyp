# binding.gyp
{
  "targets": [
    { 
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")"
      ], 
      "target_name": "./combat_simul",

      # 여기서 타겟 소스파일을 지정합니다.
      "sources": [ "src/combat_simul.cpp", "src/Object.cpp", "src/Party.cpp", "src/Skill.cpp", "src/command.cpp", "src/commandq.cpp" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}