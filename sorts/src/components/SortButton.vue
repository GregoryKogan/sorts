<template>
  <v-btn @click="sort" variant="tonal" color="primary" size="large"
    >Sort!</v-btn
  >
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SortButton",
  methods: {
    sort() {
      window.postMessage(
        JSON.stringify({
          to: "cpp",
          message: {
            action: "sort",
          },
        }),
        "*"
      );
    },
  },
});
</script>
