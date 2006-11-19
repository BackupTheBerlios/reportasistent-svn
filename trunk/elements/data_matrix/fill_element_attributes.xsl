<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
       

    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>
   
	
	<xsl:template match="data_matrix">
				
								
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
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='record_count'">
								<xsl:text>Záznamů</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='integer_count'">
								<xsl:text>Sloupců Integer</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='float_count'">
								<xsl:text>Sloupců Float</xsl:text>
							</xsl:when>

              <xsl:when test="name()='string_count'">
                <xsl:text>Sloupců String</xsl:text>
              </xsl:when>

              <xsl:when test="name()='boolean_count'">
                <xsl:text>Sloupců Boolean</xsl:text>
              </xsl:when>

              <xsl:when test="name()='date_count'">
                <xsl:text>Sloupců Date</xsl:text>
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

              <xsl:when test="name()='record_count'">
                <xsl:text>Records</xsl:text>
              </xsl:when>

              <xsl:when test="name()='integer_count'">
                <xsl:text>Columns Integer</xsl:text>
              </xsl:when>

              <xsl:when test="name()='float_count'">
                <xsl:text>Columns Float</xsl:text>
              </xsl:when>

              <xsl:when test="name()='string_count'">
                <xsl:text>Columns String</xsl:text>
              </xsl:when>

              <xsl:when test="name()='boolean_count'">
                <xsl:text>Columns Boolean</xsl:text>
              </xsl:when>

              <xsl:when test="name()='date_count'">
                <xsl:text>Columns Date</xsl:text>
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
