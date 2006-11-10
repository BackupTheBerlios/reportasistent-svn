<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          


	<!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>	
	
	
	
	<xsl:template match="task">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>

				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
	
	
	
	
	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">


			<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Datab�ze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datov� matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jm�no �lohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Typ �lohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_state'">
								<xsl:text>Stav</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_total_time'">
								<xsl:text>Celkov� �as</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_start_time'">
								<xsl:text>Za��tek testu</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='num_hyp'">
								<xsl:text>Po�et hypot�z</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='num_tests'">
								<xsl:text>Po�et verifikac�</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Task type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_state'">
								<xsl:text>State</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_total_time'">
								<xsl:text>Total time</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='gen_start_time'">
								<xsl:text>Start time</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='num_hyp'">
								<xsl:text>Hypotheses count</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='num_tests'">
								<xsl:text>Number of verifications</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->



	
					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{name()}" value="{.}" label="{$label}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->



</xsl:stylesheet>
