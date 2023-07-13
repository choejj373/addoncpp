# Node.js addon c++

python 3.11.4
visual studio 2019

# 네이티브 애드온 빌드 툴
npm install -g node-gyp

# cpp 컴파일시 필요
npm install node-addon-api

# 빌드 옵션
binding.gyp 수정

# 빌드
node-gyp rebuild

# 실행
node app.js