<template>
  <canvas
    id="_sdl-canvas"
    style="width: 100%; height: 100%"
    oncontextmenu="event.preventDefault()"
    tabindex="-1"
  ></canvas>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SDLCanvas",
  mounted() {
    let oldScript = document.getElementById("attach-wasm-to-canvas");
    if (oldScript) oldScript.remove();

    let script = document.createElement("script");
    script.type = "text/javascript";
    script.id = "attach-wasm-to-canvas";
    script.text = `
        let Module;
        Main({
          canvas: (() => document.getElementById("_sdl-canvas"))(),
        }).then((m) => { Module = m; m.callMain(); });`;
    document.body.appendChild(script);
  },
});
</script>
