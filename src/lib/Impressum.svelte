<script lang="ts">
	import { fade } from 'svelte/transition';

    function close() {
		console.log('close');
		show = false;
	}

    export let show = false; 

</script>

<div
	class=""
	transition:fade
>
	<div class="font-josefin flex flex-col h-[500px]">
		<!-- Header -->
		<div class="w-full text-center text-3xl font-semibold text-white">Impressum</div>
        <hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />

		<!-- Main -->
		<div class="grow overflow-auto px-4 border-blue-500">
			<div>
                <article in:fade class="mx-1 prose">

                <h2>Kontakt</h2>
                <address>
                    Prof. Dr. Dirk W. Hoffmann<br>
                    Hochschule Karlsruhe<br>
                    Moltkestraße 30<br>
                    D - 76133 Karlsruhe<br>
                    Germany
                </address>
				<h2>Datenschutz</h2>
                <p>
					Durch die Nutzung unserer Website erklären Sie sich mit der Erhebung, Verarbeitung und
					Nutzung von Daten gemäß der nachfolgenden Beschreibung einverstanden. Unsere Website kann
					grundsätzlich ohne Registrierung besucht werden. Dabei werden Daten wie beispielsweise
					aufgerufene Seiten bzw. Namen der abgerufenen Datei, Datum und Uhrzeit zu statistischen
					Zwecken auf dem Server gespeichert, ohne dass diese Daten unmittelbar auf Ihre Person
					bezogen werden. Personenbezogene Daten, insbesondere Name, Adresse oder E-Mail-Adresse
					werden soweit möglich auf freiwilliger Basis erhoben. Ohne Ihre Einwilligung erfolgt keine
					Weitergabe der Daten an Dritte.
				</p>
				<h2>Hosting</h2>
				<p>
					Diese Webseite wird gehostet auf Servern der Github Inc., 88 Colin P Kelly Jr. Street, San
					Francisco, CA 94107, USA. GitHub kann beim Aufruf dieser Webseiten technische
					Informationen inklusive ihrer IP Adresse aufzeichnen. Weitere Informationen zum Umgang mit
					Nutzerdaten finden Sie in der
					<a href="https://help.github.com/articles/github-privacy-policy"
						>Datenschutzerklärung von GitHub</a
					>.
				</p>
                </article>
			</div>
		</div>

		<!-- Footer -->
        <hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />
		<div class="w-full flex justify-center">
			<button class="btn btn-primary" on:click={close}>Close</button>
		</div>
	</div>
</div>
