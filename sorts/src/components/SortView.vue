<template>
  <v-container>
    <SortHeader :name="name" :link="link" />
    <h3>Time complexity {{ timeComplexity }}</h3>
    <h3>Space complexity {{ spaceComplexity }}</h3>
    <br />
    <p>{{ formatter.format(store.comparisons) }} comparisons <br /></p>
    <p v-if="showSwaps">{{ formatter.format(store.swaps) }} swaps</p>
    <SDLCanvas />
    <p>FPS: {{ store.frameRate }}</p>
    <br />
    <v-row justify="center"><SortButton /></v-row>
    <br />
    <v-col>
      <p>Number of elements: {{ formatter.format(store.sequenceLength) }}</p>
      <v-slider
        v-model="mappedSequenceLength"
        min="0"
        max="1"
        color="secondary"
      ></v-slider>
      <p>
        Steps per second:
        {{ formatter.format(store.stepsPerSecond) }}
      </p>
      <v-slider
        v-model="mappedStepsPerSecond"
        min="0"
        max="1"
        color="secondary"
      ></v-slider>
    </v-col>
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useAppStore } from "@/store/app";
import SortHeader from "@/components/SortHeader.vue";
import SDLCanvas from "@/components/SDLCanvas.vue";
import SortButton from "@/components/SortButton.vue";

export default defineComponent({
  name: "SortView",
  components: {
    SortHeader,
    SDLCanvas,
    SortButton,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
  props: {
    name: {
      type: String,
      required: true,
    },
    link: {
      type: String,
      required: true,
    },
    timeComplexity: {
      type: String,
      required: true,
    },
    spaceComplexity: {
      type: String,
      required: true,
    },
    showSwaps: {
      type: Boolean,
      required: false,
      default: true,
    },
    maxSequenceLength: {
      type: Number,
      required: false,
      default: 10000,
    },
    maxStepsPerSecond: {
      type: Number,
      required: false,
      default: 10000000,
    },
    algorithm: {
      type: String,
      required: true,
    },
  },
  data: () => ({
    sequenceLengthMappingParameter: 0,
    stepsPerSecondMappingParameter: 0,
    formatter: Intl.NumberFormat("en-US", {
      notation: "compact",
      compactDisplay: "short",
    }),
  }),
  created() {
    this.setDefaults();
  },
  methods: {
    setDefaults() {
      this.store.setSortAlgorithm(this.algorithm);
      this.store.setSequenceLength(100);
      this.store.setStepsPerSecond(100);

      this.sequenceLengthMappingParameter = this.reverseExponentialMap(
        3,
        this.maxSequenceLength,
        this.store.sequenceLength
      );
      this.stepsPerSecondMappingParameter = this.reverseExponentialMap(
        1,
        this.maxStepsPerSecond,
        this.store.stepsPerSecond
      );
    },
    exponentialMap(min: number, max: number, t: number) {
      const steepness = 3;
      const exp_t = (Math.exp(Math.pow(t, steepness)) - 1) / (Math.E - 1);
      return exp_t * (max - min) + min;
    },
    reverseExponentialMap(min: number, max: number, t: number) {
      const steepness = 3;
      const exp_t = Math.log(t / (max - min) + 1) / Math.log(Math.E);
      return Math.pow(exp_t, 1 / steepness);
    },
  },
  computed: {
    mappedSequenceLength: {
      get() {
        return this.sequenceLengthMappingParameter;
      },
      set(value: number) {
        this.sequenceLengthMappingParameter = value;
        this.store.setSequenceLength(
          Math.round(this.exponentialMap(3, this.maxSequenceLength, value))
        );
      },
    },
    mappedStepsPerSecond: {
      get() {
        return this.stepsPerSecondMappingParameter;
      },
      set(value: number) {
        this.stepsPerSecondMappingParameter = value;
        this.store.setStepsPerSecond(
          Math.round(this.exponentialMap(1, this.maxStepsPerSecond, value))
        );
      },
    },
  },
});
</script>
