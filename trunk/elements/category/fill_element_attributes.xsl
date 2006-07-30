<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
          
	<!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>	
	
	
	
	<xsl:template match="category">
				
				
				
				
				
				<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:text>Definice kategorie</xsl:text>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:text>Definition of category</xsl:text>
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
				

				
				
				
				<element_attributes>
				
		
				<!-- atributy-->
				<xsl:apply-templates select="@*"/>
				
				
				<!-- podelementy-->
				<xsl:element name="attribute">
					<xsl:attribute name="name">
						<xsl:value-of select="name()" />
					</xsl:attribute>
					<xsl:attribute name="value">
						<xsl:apply-templates select="ctgr_def"/>
					</xsl:attribute>
					<xsl:attribute name="label">
						<xsl:value-of select="$label" />
					</xsl:attribute>
  				</xsl:element>



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
							
							<xsl:when test="name()='attr_name'">
								<xsl:text>Jméno atributu</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_name'">
								<xsl:text>Jméno kategorie</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_type'">
								<xsl:text>Typ kategorie</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_freq'">
								<xsl:text>Frekvence</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='bool_type'">
								<xsl:text>Boolský typ</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='def_length'">
								<xsl:text>Délka definice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_def'">
								<xsl:text>Definice kategorie</xsl:text>
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
							
							<xsl:when test="name()='attr_name'">
								<xsl:text>Attribute name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_name'">
								<xsl:text>Category name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_type'">
								<xsl:text>Category type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_freq'">
								<xsl:text>Frequency</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='bool_type'">
								<xsl:text>Boolean type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='def_length'">
								<xsl:text>Definition length</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_def'">
								<xsl:text>Definition of category</xsl:text>
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







	<!-- vypise polozky kategorie -->
	<xsl:template match="ctgr_def">
		<xsl:if test="position()!=1">
  			<xsl:text disable-output-escaping="no">; </xsl:text> 
  		</xsl:if>
  		<xsl:value-of select="@definition" /> 
  	</xsl:template>

	





</xsl:stylesheet>
