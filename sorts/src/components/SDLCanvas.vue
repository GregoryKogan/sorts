<template>
  <canvas
    id="_sdl-canvas"
    style="
      width: 100%;
      aspect-ratio: 16 / 9;
      max-height: 65vh;
      pointer-events: none;
    "
    oncontextmenu="event.preventDefault()"
    tabindex="-1"
  ></canvas>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SDLCanvas",
  mounted() {
    let scriptText;

    let oldScript = document.querySelector("#attach-wasm-to-canvas");
    if (oldScript) {
      scriptText = `
        Main({
          canvas: (() => document.querySelector("#_sdl-canvas"))(),
        }).then((m) => { Module = m; m.callMain(); });`;
      oldScript.remove();
    } else {
      scriptText = `
        let Module;
        Main({
          canvas: (() => document.querySelector("#_sdl-canvas"))(),
        }).then((m) => { Module = m; m.callMain(); });`;
    }

    let script = document.createElement("script");
    script.type = "text/javascript";
    script.id = "attach-wasm-to-canvas";
    script.text = scriptText;
    document.body.appendChild(script);
  },
});
</script>
